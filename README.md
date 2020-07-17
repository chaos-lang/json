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
