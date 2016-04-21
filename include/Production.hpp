#pragma once

enum ProductionType {
    ptUnit,
    ptWeapon,
    ptStructure,
    ptUpgrade
};

class ProductionOption {
public:
    ProductionType type;

    // Unit:

    // Index of the MOBTemplate.
    // TODO: Mob references should be stored better. Convenience over speed here.
    //    As in, this requires using the reference number of the MOBTemplate in
    //      the files for this production option, and subsequently this structure reference.
    uint64_t MOBIndex;

    // Structure:
    uint64_t StructureIndex;

    // Upgrade:
    // TODO: Implement player-based modifiers.

    // Weapon:
    // This is a little ways off. No need to put it on the to do list yet.

    // Time taken for this production option to be produced. In seconds.
    float timeNeeded;
};
