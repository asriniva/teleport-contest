        vault(services, name, ...args) {
            let environment = vaultEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createVaultEnvironment(services, layouts.vault);
                vaultEnvironments.set(services.moduleKey, environment);
            }
            if (['newegd', 'free_egd', 'clear_fcorr', 'restfakecorr',
                 'parkguard', 'grddead', 'in_fcorridor', 'uleftvault',
                 'find_guard_dest', 'wallify_vault', 'gd_mv_monaway',
                 'gd_pick_corridor_gold', 'gd_move_cleanup', 'gd_letknow',
                 'gd_move'].includes(name))
                args[0] = environment.monster(args[0]);
            if (name === 'move_gold') args[0] = environment.object(args[0]);
            if (name === 'vault_occupied') args[0] = environment.address(args[0]);
            if (name === 'find_guard_dest') {
                args[1] = environment.coordPointer(args[1]);
                args[2] = environment.coordPointer(args[2]);
            }
            const result = withCEnvironment(environment, vault[name], ...args);
            return result?.address ?? result ?? 0;
        },
