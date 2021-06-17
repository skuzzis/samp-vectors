# Examples

There is a list of examples for SA:MP Vectors.

## Vector_Create

If you use `Vector_Create()` when you create the vector variable, you will get an error. So, you need to use `Vector_Create()` at `OnGameModeInit()`.

```pawn
new Vector:vector1;

public OnGameModeInit()
{
    vector1 = Vector_Create();
    return 1;
}
```

## foreachVector

It's like `foreach` but for vectors.

```pawn
foreachVector(vector1, i) {
    printf("%d", i);
}
```
