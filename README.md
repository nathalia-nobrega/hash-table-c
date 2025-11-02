# hash-table-c



This project implements a hash table in C using separate chaining to handle collisions. Each bucket in the table is a linked list that stores key-value pairs. The program includes functions to create the table, insert entries, search for keys, and free all allocated memory.

The hash function used is **djb2** (not the most efficient, but simple enough).


## Example Output

```
[0]: Fiona Apple → Horsegirl → Electrelane (UK)
[2]: Georgia Ellery
[5]: Tyler Hyde → May Kershaw
```

Each index represents a bucket in the table, and the arrows show chained entries that share the same hash index due to collisions.

## References

* [Hash Table — Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
* [What is a linked list and how to implement it - IME-USP, Paulo Feofiloff](https://www.ime.usp.br/~pf/algorithms/chapters/linked-lists.html)
* [hash function for string - Stack Overflow](https://stackoverflow.com/questions/7666509/hash-function-for-string?noredirect=1&lq=1)
* [Tabela de símbolos - IME-USP, Paulo Feofiloff](https://www.ime.usp.br/~pf/mac0122-2002/aulas/symbol-table.html)
* [Tabelas de dispersão (hash tables) - IME-USP, Paulo Feofiloff](https://www.ime.usp.br/~pf/mac0122-2002/aulas/hashing.html)
* [Coelho, F. J, M. Tabelas Hash, Disciplina Algoritmos e Estruturas de Dados 1,
Universidade do Estado do Amazonas, EST - Núcleo de
Computação: Manaus/AM, Brasil, 2025.]()
