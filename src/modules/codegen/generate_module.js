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
const ask_user_with_bool = () => {
    const ans = ask_user_with_string().toLowerCase();

    if (ans == "y" || ans == "yes") {
       return true;
    }

    return false;
}

let project_name = "";

if (process.argv.length == 2) {
    display_help();
}

project_name = process.argv[2];

console.log(`! Generating module "${project_name}"`);

if (fs.existsSync(project_name) && !SAFE_MODE) {
    console.log(`! Module "${project_name}" already exist!`);
    process.stdout.write("? Do you want to recreate this project? (y/N): ")

    const ans = ask_user_with_bool();
    if (ans) {
        console.log(`! Replacing project "${project_name}"`);

        fs.rmSync(project_name, {recursive: true});
    } else {
        process.exit(1);
    }
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

var cmd_features = {};

commands.forEach(cmd => {
    console.log(`! Configuring "${cmd}" command`);
    process.stdout.write("? Do you want this command to be a fullscreen application (y/N): ")

    const is_fullscreen = ask_user_with_bool();
    let is_windowed = false;
    
    if (!is_fullscreen) {
        process.stdout.write("\n? Do you want this command to be a windowed applcation (y/N): ")
        
        is_windowed = ask_user_with_bool();
    }

    cmd_features[cmd] = {
        "fullscreen": is_fullscreen,
        "windowed": is_windowed
    }
})

console.log(`! Generating source code\n  @ module.c`);

let register_commands = "";
let command_includes = "";

commands.forEach(cmd => {
    register_commands += `    info->register_command("${cmd}", "Codegenned ${cmd} command", false, ${cmd}_command);\n`

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

console.log("  @ state.c");

const state_c_src = `
#include <nt5emul/modules/${project_name}/state.h>

struct module_state _state = {0};
`

console.log("  @ state.h");

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

extern struct module_state _state;
`
console.log("! Saving files: module.c ; state.c ; state.h");

if (!SAFE_MODE) {
    fs.writeFileSync(`${src_dir}/module.c`, module_c_src);
    fs.writeFileSync(`${src_dir}/state.c`, state_c_src);
    fs.writeFileSync(`${incl_dir}/state.h`, state_h_src);
}

commands.forEach(cmd => {
    console.log(`  @ ${cmd}_command.c`);

    let cmd_includes = "";
    let cmd_fullscreen = "";
    let cmd_windowed = "";

    let cmd_draw_header = "";
    let cmd_update_header = "";

    if (cmd_features[cmd].fullscreen) {
        cmd_includes += `#include <nt5emul/renderer.h>\n`

        cmd_draw_header = "if (_state.old_draw) _state.old_draw(_state.old_ctx);"
        cmd_update_header = "if (_state.old_update) _state.old_update(_state.old_ctx);"

        cmd_fullscreen = 
`
renderer_state_t *st = _ntRendererGetState();
    int index = 0; // replace with your own layer index

    _state.old_draw = st->layers[index].draw;
    _state.old_update = st->layers[index].update;
    _state.old_ctx = st->layers[index].user;

    st->layers[index].draw = ${cmd}_draw;
    st->layers[index].update = ${cmd}_update;
`
    }
    if (cmd_features[cmd].windowed) {
        cmd_includes += `#include <nt5emul/dwm/context.h>\n`
        cmd_includes += `#include <nt5emul/dwm/window.h>\n`

        cmd_windowed = 
`
struct dwm_window wnd = _ntCreateWindow("${cmd}", (Vector2){500, 150});

    wnd.draw = ${cmd}_draw;
    wnd.update = ${cmd}_update;

    wnd.filled.state = true;
    wnd.filled.ability = true;

    wnd.position = (Vector2){50, 50};
    
    _ntPushWindow(_ntDwmGetGlobal(), wnd);
`
    }

    let cmd_c_src = 
`
#include <nt5emul/modules/${project_name}/state.h>
#include <nt5emul/modules/${project_name}/${cmd}_command.h>
${cmd_includes}

bool ${cmd}_command(void *data) {
    ${cmd_fullscreen}
    ${cmd_windowed}

    return true;
}
`

    if (cmd_features[cmd].fullscreen || cmd_features[cmd].windowed) {
        const cmd_draw = 
`
void ${cmd}_draw(void *ctx) {
    ${cmd_draw_header}
}
`
        const cmd_update = 
`
void ${cmd}_update(void *ctx) {
    ${cmd_update_header}
}
`

        cmd_c_src += cmd_draw;
        cmd_c_src += cmd_update;
    }

    console.log(`  @ ${cmd}_command.h`);

    const cmd_h_src = 
`
#pragma once
    
bool ${cmd}_command(void *data);
void ${cmd}_update(void *ctx);
void ${cmd}_draw(void *ctx);
`

    console.log(`! Saving files: ${cmd}_command.c ; ${cmd}_command.h`)

    if (!SAFE_MODE) {
        fs.writeFileSync(`${src_dir}/${cmd}_command.c`, cmd_c_src);
        fs.writeFileSync(`${incl_dir}/${cmd}_command.h`, cmd_h_src);
    }
})

console.log(`! Module has been codegenned successfully`)