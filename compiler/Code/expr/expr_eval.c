#include "library.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "dump_ast.h"

uint64_t *state;

uint64_t *get_element(uint64_t *id) {
    uint64_t *list;
    uint64_t *elt;

    list = state;
    while (!is_empty(list)) {
        elt = get_elt(list);
        if (string_compare(string_get(fst(elt)), id) == 1) {
            return elt;
        }
        list = next_elt(list);
    }

    return NULL;
}

uint64_t lookup(uint64_t *id) {
    uint64_t *elt;

    elt = get_element(id);
    if (elt == NULL) {
        printf1((uint64_t *) "Undefined id in state: %s\n", id);
        exit(-1);
    }

    return int_get(snd(elt));
}

void set(uint64_t *id, uint64_t val) {
    uint64_t *elt;

    elt = get_element(id);
    if (elt == NULL) {
        state = cons(pair(make_string(id), make_int(val)), state);
    } else {
        array_set(elt, 2, make_int(val));
    }
}

uint64_t calculate(uint64_t *elt) {
    uint64_t type = int_get(fst(elt));
    if (type == EINT) { // TYPE_PAIR
        return int_get(snd(elt));
    } else if (type == EVAR) {
        return lookup(string_get(snd(elt)));
    } else if (type == EADD) { // TYPE_TRIPLE
        return calculate(snd(elt)) + calculate(thr(elt));
    } else if (type == ESUB) {
        return calculate(snd(elt)) - calculate(thr(elt));
    } else if (type == EMUL) {
        return calculate(snd(elt)) * calculate(thr(elt));
    } else if (type == EMOD) {
        return calculate(snd(elt)) % calculate(thr(elt));
    } else {
        printf1((uint64_t *) "Unknown type: %d\n", &type);
        exit(-1);
        return 0;
    }
}


uint64_t eval_ast(uint64_t * ast) {
    /* Initialisation de l'état */
    state = nil();

    /* Assignments */
    uint64_t * assign = fst(ast);
    uint64_t * l = assign;
    uint64_t * id;
    uint64_t * elt;
    uint64_t
    val;

    while (!is_empty(l)) {
        elt = get_elt(l);
        id = string_get(fst(elt));
        val = calculate(snd(elt));

        set(id, val);
        l = next_elt(l);
    }

    /* Expressions */
    uint64_t * expr = snd(ast);
    return calculate(expr);
}
