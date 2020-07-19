JSON library of the Chaos langauge. You can install this spell with:

```bash
occultist install json
```

and import it with:

```chaos
import json
```

## Dictionary operations

### list json.keys(dict d)

Return all the keys in dictionary `d`:

```chaos
kaos> dict a = {'a': 1, 'b': 2, 'c': 3}
kaos> json.keys(a)
['a', 'b', 'c']
```

### list json.values(dict d)

Return all the values in dictionary `d`:

```chaos
kaos> dict a = {'a': 1, 'b': 2, 'c': 3}
kaos> json.values(a)
[1, 2, 3]
```

### dict json.flip(dict d)

Exchanges all keys with their associated values in dictionary `d`:

```chaos
kaos> dict a = {'a': 1, 'b': 2, 'c': 3}
kaos> json.flip(a)
{'1': 'a', '2': 'b', '3': 'c'}
```

## JSON related

### str json.encode(dict d)

Return a string containing the JSON representation of dictionary `d`:

```chaos
kaos> dict a = {'a': 1, 'b': 2, 'c': 3}
kaos> str json_encoded = json.encode(a)
kaos> json_encoded
{"a": 1, "b": 2, "c": 3}
```

### dict json.decode(str json)

Turn JSON string `json` into a dictionary that Chaos language understands:

```chaos
kaos> str b = "{'d': 4, 'e': 5, 'f': 6}"
kaos> dict json_decoded = json.decode(b)
kaos> json_decoded
{'d': 4, 'e': 5, 'f': 6}
```

## Searching & Replacing

### str json.search(dict d, any x)

Searches the dictionary `d` for a given value `x` and returns the first corresponding key if successful. Returns an empty string `""` if unsuccessful:

```chaos
kaos> dict a = {'a': 1, 'b': 2, 'c': 3}
kaos> json.search(a, 2)
b
kaos> dict c = {'a': 'foo', 'b': 'bar', 'c': 'baz'}
kaos> json.search(c, 'baz')
c
kaos> json.search(c, 'jazz')

```
