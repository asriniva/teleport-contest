        topten(services, name, ...args) {
            let environment = toptenEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createToptenEnvironment(services, layouts.topten);
                toptenEnvironments.set(services.moduleKey, environment);
            }
            if (name === 'formatkiller') args[0] = environment.address(args[0]);
            if (name === 'observable_depth') args[0] = environment.level(args[0]);
            if (['readentry', 'writeentry', 'writexlentry'].includes(name)) {
                args[0] = environment.address(args[0]);
                args[1] = environment.entry(args[1]);
            }
            if (name === 'discardexcess') args[0] = environment.address(args[0]);
            if (name === 'free_ttlist') args[0] = environment.entry(args[0]);
            if (['encode_extended_achievements', 'encode_extended_conducts',
                 'add_achieveX'].includes(name))
                args[0] = environment.address(args[0]);
            if (name === 'outentry') args[1] = environment.entry(args[1]);
            if (name === 'score_wanted') {
                args[2] = environment.entry(args[2]);
                args[4] = environment.stringArray(args[4]);
            }
            if (name === 'prscore') args[1] = environment.stringArray(args[1]);
            if (name === 'tt_oname') args[0] = environment.object(args[0]);
            if (name === 'tt_doppel') args[0] = environment.monster(args[0]);
            const result = withCEnvironment(environment, topten[name], ...args);
            return result?.address ?? result ?? 0;
        },
