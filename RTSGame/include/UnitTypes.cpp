#include "UnitTypes.hpp"

WeaponClass weaponClass(std::string name) {
	// Convert to lower case.
	std::transform(name.begin(), name.end(), name.begin(), tolower);

	if (!name.compare("melee"))
		return WeaponClass::WC_Melee;

	else if (!name.compare("slashing"))
		return WeaponClass::WC_Slashing;

	else if (!name.compare("grenade"))
		return WeaponClass::WC_Grenade;

	else if (!name.compare("smallarms"))
		return WeaponClass::WC_Smallarms;

	else if (!name.compare("heavyrifle"))
		return WeaponClass::WC_Heavyrifle;

	else if (!name.compare("cannon"))
		return WeaponClass::WC_Cannon;

	else if (!name.compare("autocannon"))
		return WeaponClass::WC_AutoCannon;

	else if (!name.compare("missile"))
		return WeaponClass::WC_Missile;

	else {
		std::cout << "Invalid weapon class, \""
			<< name << "\"" << std::endl;
		return WeaponClass::WC_UNKNOWN;
	}
}