const fs = require("fs");
const readline_sync = require('readline-sync');

const SAFE_MODE = false;

if (SAFE_MODE) {
    console.log("! Running in safe mode !\n")
}

const display_help = () => {
    console.log("? generate_module.js <project name>");

    process.exit(1);
}

const ask_user_with_string = () => {
    return readline_sync.question("");
}

let project_name = "";

if (process.argv.length == 2) {
    display_help();
}

project_name = process.argv[2];

console.log(`! Generating module "${project_name}"`);

if (fs.existsSync(project_name) && !SAFE_MODE) {
    console.log(`! Module "${project_name}" already exist!`);

    process.exit(1);
}

console.log(`! Creating directory structure`);

const incl_dir = `${project_name}/include/nt5emul/modules/${project_name}`
const src_dir = `${project_name}/src`

if (!SAFE_MODE) {
    fs.mkdirSync(project_name);
    fs.mkdirSync(src_dir);
    fs.mkdirSync(`${project_name}/include`);
    fs.mkdirSync(`${project_name}/include/nt5emul`);
    fs.mkdirSync(`${project_name}/include/nt5emul/modules`);
    fs.mkdirSync(incl_dir);
}

console.log(`? Type commands you want to add\n  Type "stop" to continue:`);

let commands = [];

for (;;) {
    const cmd = ask_user_with_string();

    if (cmd == "stop") {
        break;
    }

    commands.push(cmd);
}

console.log(`! Generating source code\n@ module.c`);

let register_commands = "";
let command_includes = "";

commands.forEach(cmd => {
    register_commands += `  info->register_command("${cmd}", "Codegenned ${cmd} command", false, ${cmd}_command);\n`

    command_includes += `#include <nt5emul/modules/${project_name}/${cmd}_command.h>\n`
})


const module_c_src = `
#include <nt5emul/modules/${project_name}/state.h>
${command_includes}

void init(cterm_t *info) {
    _state.runtime = info;

${register_commands}

    return;
}

SET_INFORMATION("${project_name}", "Codegenned project", "1.00")
`

console.log("@ state.c");

const state_c_src = `
#include <nt5emul/modules/${project_name}/state.h>

struct module_state _state = {0};
`

console.log("@ state.h");

const state_h_src = `
#pragma once

#include <cterm/applications/api.h>

struct module_state {
    cterm_t *runtime;

    bool execution_lock;

    void (*old_draw)(void *user);
    void (*old_update)(void *user);
    void *old_ctx;
};
`
console.log("! Saving files: module.c ; state.c ; state.h");

if (!SAFE_MODE) {
    fs.writeFileSync(`${src_dir}/module.c`, module_c_src);
    fs.writeFileSync(`${src_dir}/state.c`, state_c_src);
    fs.writeFileSync(`${incl_dir}/state.h`, state_h_src);
}

commands.forEach(cmd => {
    console.log(`@ ${cmd}_command.c`);

    const cmd_c_src = 
`
#include <nt5emul/modules/${project_name}/state.h>
#include <nt5emul/modules/${project_name}/${cmd}_command.h>

bool ${cmd}_command(void *data) {
    return true;
}
`

    console.log(`@ ${cmd}_command.h`);

    const cmd_h_src = 
`
#pragma once
    
bool ${cmd}_command(void *data);
`

    console.log(`! Saving files: ${cmd}_command.c ; ${cmd}_command.h`)

    if (!SAFE_MODE) {
        fs.writeFileSync(`${src_dir}/${cmd}_command.c`, cmd_c_src);
        fs.writeFileSync(`${incl_dir}/${cmd}_command.h`, cmd_h_src);
    }
})

console.log(`! Module has been codegenned successfully`)