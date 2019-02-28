#include "config.hpp"
#include "adaptivepurepursuit.hpp"
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
	// if (closestPointAndDistance.distance.convert(inch) == 0) {
	// 	newLookahead = lookahead;
	// } else {
	// 	newLookahead = (double) lookahead / (closestPointAndDistance.distance.convert(inch) * lookaheadKf);
	// }
	newLookahead = (newLookahead < 0) ? 1 : newLookahead;
	//newLookahead = (newLookahead > lookahead) ? lookahead : newLookahead;

	int requiredPosition = closestPointAndDistance.point.t;
	target = path->pointAt(requiredPosition + newLookahead);

	double distTolookaheadPoint =
		sqrt(pow(target.x.convert(inch) - robotPosition.x.convert(inch), 2) + pow(target.y.convert(inch) - robotPosition.y.convert(inch), 2));

	straightController->setTarget(distTolookaheadPoint);

	double forwardPower = straightController->step(0);
	// QAngle bearing =
	// 	std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
	// 			   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
	// 	radian;
	QAngle bearing =
		std::atan2((this->target.x.convert(inch) - robotPosition.x.convert(inch)),
				   (this->target.y.convert(inch) - robotPosition.y.convert(inch))) *
		radian;

	direction = 1;

	QAngle currBearingAngle = std::atan2(sin(odometry::currAngle.convert(radian)), cos(odometry::currAngle.convert(radian))) * radian;

	double angleError = bearing.convert(radian) - currBearingAngle.convert(radian);
	angleError = std::atan2(sin(angleError), cos(angleError));

	//if (target.t == path->getResolution())
	//{
	if (angleError * 180.0 / PI > 90)
	{
		angleError -= PI;
		// angleError *= -1;
		direction *= -1;
	}
	else if (angleError * 180.0 / PI < -90)
	{
		angleError += PI;
		// angleError *= -1;
		direction *= -1;
	}
	//}

	//turnController->setTarget(bearing.convert(degree));
	turnController->setTarget(angleError);

	// double turnPower = turnController->step(odometry::currAngle.convert(degree));
	// double turnPower = turnController->step(currHeading.convert(degree));
	//double turnPower = turnController->step(turnControllerPV.convert(degree));
	double turnPower = turnController->step(0);

	//printf("Bearing: %f, ", bearing.convert(degree));
	//printf("angleError: %f, ", (angleError * 180.0/PI));
	//printf("Forward: %f, Turn: %f, ", forwardPower, turnPower);
	//printf("Angle: %1.2f\n", currBearingAngle.convert(degree));


	chassis.driveVector(direction * forwardPower, turnPower); // TODO CHASSIS MODEL IN CONSTRUCTOR INSTEAD OF HERE
}
path::Point AdaptivePurePursuit::getPointTarget()
{
	return target;
}

bool AdaptivePurePursuit::isSettled()
{
	path::Point endPoint = path->pointAt(path->getResolution());
	double distance = sqrt(pow(endPoint.x.convert(inch) - odometry::currX.convert(inch), 2) + pow(endPoint.y.convert(inch) - odometry::currY.convert(inch), 2));
	return (distance < 2);
}

void AdaptivePurePursuit::setKf(double kf)
{
	this->lookaheadKf = kf;
}
} // namespace pathfollowing
