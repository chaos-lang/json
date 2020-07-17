#include <stdlib.h>

#include "Chaos.h"


// Dictionary operations

// list json.keys(dict d)

char *keys_params_name[] = {
    "d"
};
unsigned keys_params_type[] = {
    K_DICT
};
unsigned short keys_params_length = (unsigned short) sizeof(keys_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_keys()
{
    unsigned long dict_length = kaos.getDictLength(keys_params_name[0]);
    enum Type dict_type = kaos.getDictType(keys_params_name[0]);

    kaos.startBuildingList();

    for (unsigned long i = 0; i < dict_length; i++) {
        char *key = kaos.getDictKeyByIndex(keys_params_name[0], (long long) i);
        kaos.createVariableString(NULL, key);
        free(key);
    }

    kaos.returnList(dict_type);
    return 0;
}

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;
    kaos.defineFunction("keys", K_LIST, keys_params_name, keys_params_type, keys_params_length);

    return 0;
}
