#include "adaptivepurepursuit.hpp"
// #include "config.hpp"
#include "drive.hpp"

namespace pathfollowing
{
AdaptivePurePursuit::AdaptivePurePursuit(
	std::unique_ptr<okapi::IterativePosPIDController> straight,
	std::unique_ptr<okapi::IterativePosPIDController> turn,
	int lookahead, double lookaheadKf) : straightController(std::move(straight)),
										 turnController(std::move(turn)),
										 mainLookahead(lookahead),
										 lookahead(lookahead),
										 lookaheadKf(lookaheadKf),
										 direction(1),
										 angleTarget(0_deg) {}

void AdaptivePurePursuit::setPath(path::Path *path)
{
	this->path = path;
	int look = path->getLookahead();
	lookahead = (look < 0) ? mainLookahead : look;
}

void AdaptivePurePursuit::setLookahead(int lookahead)
{
	this->lookahead = lookahead;
}

void AdaptivePurePursuit::loop()
{
	using namespace okapi;

	path::Point robotPosition = {odometry::currX, odometry::currY};

	path::PointAndDistance closestPointAndDistance = path->getClosestPointAndDistance(robotPosition);

	int newLookahead = lookahead - (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	newLookahead = (newLookahead < 0) ? 1 : newLookahead;

	int requiredPosition = closestPointAndDistance.point.t;
	target = path->pointAt(requiredPosition + newLookahead);

	double distTolookaheadPoint =
		sqrt(pow(target.x.convert(inch) - robotPosition.x.convert(inch), 2) + pow(target.y.convert(inch) - robotPosition.y.convert(inch), 2));

	straightController->setTarget(distTolookaheadPoint);

	double forwardPower = straightController->step(0);
	QAngle bearing =
		std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
				   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
		radian;

	direction = 1;

	// if (bearing.convert(degree) > 90)
	// {
	// 	bearing = (bearing.convert(degree) - 180) * degree;
	// 	direction *= -1;
	// }
	// else if (bearing.convert(degree) < -90)
	// {
	// 	bearing = (bearing.convert(degree) + 180) * degree;
	// 	direction *= -1;
	// }

	QAngle turnControllerPV = odometry::currAngle;

	if (bearing.convert(radian) < 0 && turnControllerPV.convert(radian) > 0) {
		turnControllerPV = (turnControllerPV.convert(radian) - (PI * 2)) * radian;
	}

	turnController->setTarget(bearing.convert(degree));

	// double turnPower = turnController->step(odometry::currAngle.convert(degree));
	// double turnPower = turnController->step(currHeading.convert(degree));
	double turnPower = turnController->step(turnControllerPV.convert(degree));


	printf("%f\n", bearing.convert(degree)); //lul that's big brain

	chassis.driveVector(direction * forwardPower, turnPower); // TODO CHASSIS MODEL IN CONSTRUCTOR INSTEAD OF HERE
}

okapi::QAngle AdaptivePurePursuit::getAngleTarget() {
	return angleTarget;
}
} // namespace pathfollowing
