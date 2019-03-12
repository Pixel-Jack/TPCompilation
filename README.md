# Commands

# Docker
at the root
```
docker-compose up --build -d --remove-orphans
docker-compose exec main bash
```
Now you are logged in the container

To set down
```
docker-compose down
```

# Lexeur
In the container
go in /home/work and choose your repo

Regenerate Grammar
```
 ./parser_generator -g expr_grammar.g -pc expr_parser.c -ph expr_parser.h -pdir expr/
 ```

 Change ast.c
 ```
 make
 ./cstar -c tests/test6.e -show-ast tests/test6.dot
```