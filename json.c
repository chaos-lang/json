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

// list json.values(dict d)

char *values_params_name[] = {
    "d"
};
unsigned values_params_type[] = {
    K_DICT
};
unsigned short values_params_length = (unsigned short) sizeof(values_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_values()
{
    unsigned long dict_length = kaos.getDictLength(values_params_name[0]);
    enum Type dict_type = kaos.getDictType(values_params_name[0]);

    kaos.startBuildingList();

    for (unsigned long i = 0; i < dict_length; i++) {
        char *key = kaos.getDictKeyByIndex(values_params_name[0], (long long) i);
        enum ValueType value_type = kaos.getDictElementValueType(values_params_name[0], key);
        char *value = NULL;
        switch (value_type)
            {
                case V_BOOL:
                    kaos.createVariableBool(NULL, kaos.getDictElementBool(values_params_name[0], key));
                    break;
                case V_INT:
                    kaos.createVariableInt(NULL, kaos.getDictElementInt(values_params_name[0], key));
                    break;
                case V_FLOAT:
                    kaos.createVariableFloat(NULL, kaos.getDictElementFloat(values_params_name[0], key));
                    break;
                case V_STRING:
                    value = kaos.getDictElementString(values_params_name[0], key);
                    kaos.createVariableString(NULL, value);
                    free(value);
                    break;
                default:
                    break;
            }
        free(key);
    }

    kaos.returnList(dict_type);
    return 0;
}

// dict json.flip(dict d)

char *flip_params_name[] = {
    "d"
};
unsigned flip_params_type[] = {
    K_DICT
};
unsigned short flip_params_length = (unsigned short) sizeof(flip_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_flip()
{
    unsigned long dict_length = kaos.getDictLength(flip_params_name[0]);
    enum Type dict_type = kaos.getDictType(flip_params_name[0]);

    kaos.startBuildingDict();

    for (unsigned long i = 0; i < dict_length; i++) {
        char *key = kaos.getDictKeyByIndex(flip_params_name[0], (long long) i);
        char *value = kaos.getDictElementStringByTypeCasting(flip_params_name[0], key);
        kaos.createVariableString(value, key);
        free(key);
        free(value);
    }

    kaos.returnDict(dict_type);
    return 0;
}

// JSON related

// str json.encode(dict d)

char *encode_params_name[] = {
    "d"
};
unsigned encode_params_type[] = {
    K_DICT
};
unsigned short encode_params_length = (unsigned short) sizeof(encode_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_encode()
{
    char *json = kaos.dumpVariableToString(encode_params_name[0], false, true, true);
    kaos.returnVariableString(json);
    return 0;
}

// dict json.decode(str json)

char *decode_params_name[] = {
    "json"
};
unsigned decode_params_type[] = {
    K_STRING
};
unsigned short decode_params_length = (unsigned short) sizeof(decode_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_decode()
{
    char *json = kaos.getVariableString(decode_params_name[0]);
    kaos.parseJson(json);
    free(json);
    return 0;
}

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;

    // Dictionary operations
    kaos.defineFunction("keys", K_LIST, keys_params_name, keys_params_type, keys_params_length);
    kaos.defineFunction("values", K_LIST, values_params_name, values_params_type, values_params_length);
    kaos.defineFunction("flip", K_DICT, flip_params_name, flip_params_type, flip_params_length);

    // JSON related
    kaos.defineFunction("encode", K_STRING, encode_params_name, encode_params_type, encode_params_length);
    kaos.defineFunction("decode", K_DICT, decode_params_name, decode_params_type, decode_params_length);

    return 0;
}
