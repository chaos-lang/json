#include <stdlib.h>
#include <string.h>

#include "Chaos.h"


// Dictionary Operations

// list json.keys(dict d)

char *keys_params_name[] = {
    "d"
};
unsigned keys_params_type[] = {
    K_DICT
};
unsigned keys_params_secondary_type[] = {
    K_ANY
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
unsigned values_params_secondary_type[] = {
    K_ANY
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
unsigned flip_params_secondary_type[] = {
    K_ANY
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


// JSON Related

// str json.encode(dict d)

char *encode_params_name[] = {
    "d"
};
unsigned encode_params_type[] = {
    K_DICT
};
unsigned encode_params_secondary_type[] = {
    K_ANY
};
unsigned short encode_params_length = (unsigned short) sizeof(encode_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_encode()
{
    char *json = kaos.dumpVariableToString(encode_params_name[0], false, true, true);
    kaos.returnVariableString(json);
    free(json);
    return 0;
}

// dict json.decode(str json)

char *decode_params_name[] = {
    "json"
};
unsigned decode_params_type[] = {
    K_STRING
};
unsigned decode_params_secondary_type[] = {
    K_ANY
};
unsigned short decode_params_length = (unsigned short) sizeof(decode_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_decode()
{
    char *json = kaos.getVariableString(decode_params_name[0]);
    kaos.parseJson(json);
    free(json);
    return 0;
}


// Searching & Replacing

// str json.search(dict haystack, any needle)

char *search_params_name[] = {
    "haystack",
    "needle"
};
unsigned search_params_type[] = {
    K_DICT,
    K_ANY
};
unsigned search_params_secondary_type[] = {
    K_ANY,
    K_ANY
};
unsigned short search_params_length = (unsigned short) sizeof(search_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_search()
{
    unsigned long dict_length = kaos.getDictLength(search_params_name[0]);

    for (unsigned long i = 0; i < dict_length; i++) {
        char *key = kaos.getDictKeyByIndex(search_params_name[0], (long long) i);
        enum ValueType value_type = kaos.getDictElementValueType(search_params_name[0], key);

        bool x_b, y_b;
        long long x_i, y_i;
        long double x_f, y_f;
        char *x_s, *y_s;

        switch (value_type)
        {
            case V_BOOL:
                x_b = kaos.getVariableBool(search_params_name[1]);
                y_b = kaos.getDictElementBool(search_params_name[0], key);
                if (x_b == y_b) {
                    kaos.returnVariableString(key);
                    free(key);
                    return 0;
                }
                break;
            case V_INT:
                x_i = kaos.getVariableInt(search_params_name[1]);
                y_i = kaos.getDictElementInt(search_params_name[0], key);
                if (x_i == y_i) {
                    kaos.returnVariableString(key);
                    free(key);
                    return 0;
                }
                break;
            case V_FLOAT:
                x_f = kaos.getVariableFloat(search_params_name[1]);
                y_f = kaos.getDictElementFloat(search_params_name[0], key);
                if (x_f == y_f) {
                    kaos.returnVariableString(key);
                    free(key);
                    return 0;
                }
                break;
            case V_STRING:
                x_s = kaos.getVariableString(search_params_name[1]);
                y_s = kaos.getDictElementString(search_params_name[0], key);
                if (strcmp(x_s, y_s) == 0) {
                    free(x_s);
                    free(y_s);
                    kaos.returnVariableString(key);
                    free(key);
                    return 0;
                }
                free(x_s);
                free(y_s);
                break;
            default:
                break;
        }
        free(key);
    }

    kaos.returnVariableString("");
    return 0;
}

// dict json.replace(dict haystack, any needle, any replacement)

char *replace_params_name[] = {
    "haystack",
    "needle",
    "replacement"
};
unsigned replace_params_type[] = {
    K_DICT,
    K_ANY,
    K_ANY
};
unsigned replace_params_secondary_type[] = {
    K_ANY,
    K_ANY,
    K_ANY
};
unsigned short replace_params_length = (unsigned short) sizeof(replace_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_replace()
{
    unsigned long dict_length = kaos.getDictLength(replace_params_name[0]);
    enum Type dict_type = kaos.getDictType(replace_params_name[0]);

    kaos.startBuildingDict();

    for (unsigned long i = 0; i < dict_length; i++) {
        char *key = kaos.getDictKeyByIndex(replace_params_name[0], (long long) i);
        enum ValueType value_type = kaos.getDictElementValueType(replace_params_name[0], key);

        bool x_b, y_b;
        long long x_i, y_i;
        long double x_f, y_f;
        char *x_s, *y_s;
        char *replacement;

        switch (value_type)
        {
            case V_BOOL:
                x_b = kaos.getVariableBool(replace_params_name[1]);
                y_b = kaos.getDictElementBool(replace_params_name[0], key);
                if (x_b == y_b) {
                    kaos.createVariableBool(key, kaos.getVariableBool(replace_params_name[2]));
                } else {
                    kaos.createVariableBool(key, y_b);
                }
                break;
            case V_INT:
                x_i = kaos.getVariableInt(replace_params_name[1]);
                y_i = kaos.getDictElementInt(replace_params_name[0], key);
                if (x_i == y_i) {
                    kaos.createVariableInt(key, kaos.getVariableInt(replace_params_name[2]));
                } else {
                    kaos.createVariableInt(key, y_i);
                }
                break;
            case V_FLOAT:
                x_f = kaos.getVariableFloat(replace_params_name[1]);
                y_f = kaos.getDictElementFloat(replace_params_name[0], key);
                if (x_f == y_f) {
                    kaos.createVariableFloat(key, kaos.getVariableFloat(replace_params_name[2]));
                } else {
                    kaos.createVariableFloat(key, y_f);
                }
                break;
            case V_STRING:
                x_s = kaos.getVariableString(replace_params_name[1]);
                y_s = kaos.getDictElementString(replace_params_name[0], key);
                if (strcmp(x_s, y_s) == 0) {
                    replacement = kaos.getVariableString(replace_params_name[2]);
                    kaos.createVariableString(key, replacement);
                    free(replacement);
                } else {
                    kaos.createVariableString(key, y_s);
                }
                free(x_s);
                free(y_s);
                break;
            default:
                break;
        }
        free(key);
    }

    kaos.returnDict(dict_type);
    return 0;
}


// Information Functions

// num json.count(dict d)

char *count_params_name[] = {
    "d"
};
unsigned count_params_type[] = {
    K_DICT
};
unsigned count_params_secondary_type[] = {
    K_ANY
};
unsigned short count_params_length = (unsigned short) sizeof(count_params_type) / sizeof(unsigned);
int KAOS_EXPORT Kaos_count()
{
    unsigned long dict_length = kaos.getDictLength(count_params_name[0]);
    kaos.returnVariableInt((long long) dict_length);
    return 0;
}

int KAOS_EXPORT KaosRegister(struct Kaos _kaos)
{
    kaos = _kaos;

    // Dictionary Operations
    kaos.defineFunction("keys", K_LIST, K_ANY, keys_params_name, keys_params_type, keys_params_secondary_type, keys_params_length, NULL, 0);
    kaos.defineFunction("values", K_LIST, K_ANY, values_params_name, values_params_type, values_params_secondary_type, values_params_length, NULL, 0);
    kaos.defineFunction("flip", K_DICT, K_ANY, flip_params_name, flip_params_type, flip_params_secondary_type, flip_params_length, NULL, 0);

    // JSON Related
    kaos.defineFunction("encode", K_STRING, K_ANY, encode_params_name, encode_params_type, encode_params_secondary_type, encode_params_length, NULL, 0);
    kaos.defineFunction("decode", K_DICT, K_ANY, decode_params_name, decode_params_type, decode_params_secondary_type, decode_params_length, NULL, 0);

    // Searching & Replacing
    kaos.defineFunction("search", K_STRING, K_ANY, search_params_name, search_params_type, search_params_secondary_type, search_params_length, NULL, 0);
    kaos.defineFunction("replace", K_DICT, K_ANY, replace_params_name, replace_params_type, replace_params_secondary_type, replace_params_length, NULL, 0);

    // Information Functions
    kaos.defineFunction("count", K_NUMBER, K_ANY, count_params_name, count_params_type, count_params_secondary_type, count_params_length, NULL, 0);

    return 0;
}
