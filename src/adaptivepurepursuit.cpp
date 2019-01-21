#include "adaptivepurepursuit.hpp"
#include "config.hpp"

namespace pathfollowing {
    AdaptivePurePursuit::AdaptivePurePursuit(
      std::unique_ptr<okapi::IterativePosPIDController> straight,
      std::unique_ptr<okapi::IterativePosPIDController> turn,
      int lookahead, double lookaheadKf, QLength nextPointDistance) : 
	  straightController(std::move(straight)),
	  turnController(std::move(turn)),
	  mainLookahead(lookahead),
	  lookahead(lookahead),
	  lookaheadKf(lookaheadKf),
	  nextPointdistance(nextPointdistance) {}

	void AdaptivePurePursuit::setPath(path::Path *path) {
		this->path = path;
		int look = path->getLookahead();
		lookahead = (look < 0) ? mainLookahead : look;
	}

	void AdaptivePurePursuit::setLookahead(int lookahead) {
		this->lookahead = lookahead;
	}

    void AdaptivePurePursuit::loop() {
		using namespace okapi;

		path::Point robotPosition = {odometry::currX, odometry::currY};
		path::PointAndDistance closestPointAndDistance = path->getClosestPointAndDistance(robotPosition);

		int newLookahead = lookahead - (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
		newLookahead = (newLookahead < 0) ? 1 : newLookahead;

		int requiredPosition = closestPointAndDistance.point.t;
		target = path->pointAt(requiredPosition + newLookahead);

		double distTolookaheadPoint = 
			sqrt(pow((target.x.convert(inch) - robotPosition.x.convert(inch)), 2) 
			+ pow((target.y.convert(inch) - robotPosition.y.convert(inch)), 2));

		straightController->setTarget(0);

		double forwardPower = straightController->step(distTolookaheadPoint);
		QAngle heading = 
			std::atan2((this->target.y.convert(inch) - robotPosition.y.convert(inch)), 
			(this->target.x.convert(inch) - robotPosition.x.convert(inch))) * radian;

		turnController->setTarget(0);

		double turnPower = turnController->step(heading.convert(degree));

		chassis.driveVector(forwardPower, turnPower);
    }
}
