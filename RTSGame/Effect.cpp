
#include "Effect.hpp"

void EffectHandler::registerEffect(Effect effect) {
	effects.push_back(effect);

	//effects.reserve
}

void EffectHandler::loadEffect(std::string file) {

}

int EffectHandler::find (std::string name) {


	return -1; // Failure.
}

void EffectHandler::clear() {
	for (int i = 0; i < effects.size(); ++i) {
		effects[i].clear();
	}
}
