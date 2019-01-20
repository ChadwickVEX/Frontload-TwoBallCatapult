#include "adaptivepurepursuit.hpp"

namespace pathfollowing {
    AdaptivePurePursuit::AdaptivePurePursuit(
      std::unique_ptr<okapi::IterativePosPIDController> straight,
      std::unique_ptr<okapi::IterativePosPIDController> turn,
      int lookahead, double lookaheadKf) : 
	  straightController(std::move(straight)),
	  turnController(std::move(turn)),
	  lookahead(lookahead),
	  lookaheadKf(lookaheadKf) {}

	void AdaptivePurePursuit::setPath(path::Path *path) {
		this->path = path;
	}

    void AdaptivePurePursuit::loop() {

    }
}
