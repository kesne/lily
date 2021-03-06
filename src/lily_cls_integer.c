#include <inttypes.h>
#include <string.h>
#include <stdio.h>

#include "lily_alloc.h"
#include "lily_vm.h"
#include "lily_value.h"
#include "lily_seed.h"

void lily_integer_to_d(lily_vm_state *vm, uint16_t argc, uint16_t *code)
{
    lily_value **vm_regs = vm->vm_regs;
    lily_value *result_reg = vm_regs[code[0]];
    double doubleval = (double)vm_regs[code[1]]->value.integer;

    lily_move_double(result_reg, doubleval);
}

void lily_integer_to_s(lily_vm_state *vm, uint16_t argc, uint16_t *code)
{
    lily_value **vm_regs = vm->vm_regs;
    int64_t integer_val = vm_regs[code[1]]->value.integer;
    lily_value *result_reg = vm_regs[code[0]];

    char buffer[32];
    snprintf(buffer, 32, "%"PRId64, integer_val);

    lily_move_string(result_reg, lily_new_raw_string(buffer));
}

static const lily_func_seed to_d =
    {NULL, "to_d", dyna_function, "(Integer):Double", &lily_integer_to_d};

static const lily_func_seed dynaload_start =
    {&to_d, "to_s", dyna_function, "(Integer):String", &lily_integer_to_s};

static lily_class_seed integer_seed =
{
    NULL,               /* next */
    "Integer",          /* name */
    dyna_class,         /* load_type */
    0,                  /* is_refcounted */
    0,                  /* generic_count */
    &dynaload_start     /* dynaload_table */
};

lily_class *lily_integer_init(lily_symtab *symtab)
{
    return lily_new_class_by_seed(symtab, &integer_seed);
}
