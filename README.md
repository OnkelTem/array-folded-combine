# PHP array_folded_combine()

## Terms:

`SCALAR` — string or number

`[N]` — array of N elements (e.g.: `[1]` — array of one element)

`N:m` — m'th element of array of N elements

## Multiplication operation (×):

1. `SCALAR × SCALAR = { SCALAR: SCALAR }`
2. `SCALAR × [N] = { SCALAR: [N] }`
3. `[N] × SCALAR = { [N]: SCALAR }` - this is allowed, but key can not be array in most implementations (YAML/JSON/JS)
4. `[1] × [N] = [ 1 × N:1, 1 × N:2, ... , 1 × N:N ]`
5. `[1] × [1] = [ { 1 : N:1 } ]` - considered as a special case of 4, not of 7
6. `[N] × [1] = [ N:1 × 1, N:2 × 1, ... , N:N × 1 ]`
7. `[N] × [N] = { N:1 × N:1, N:2 × N:2, ... , N:N × N:N }`
8. `[M] × [N] = Undefined if M != N`

## Example:

```yaml
A: [[id, name]]
B: [[1, 'Peter'], [2, 'Max'], [3, 'Anna']]
```

`A × B` results to:

```yaml
A_B:
  - {id: 1, name: 'Peter'}
  - {id: 2, name: 'Max'}
  - {id: 3, name: 'Anna'}
```







