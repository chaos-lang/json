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
