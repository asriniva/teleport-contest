        getpos(services, name, ...args) {
            let environment = getposEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createGetposEnvironment(services, layouts.getpos, getpos);
                getposEnvironments.set(services.moduleKey, environment);
            }
            if (['getpos', 'getpos_menu'].includes(name))
                args[0] = environment.coord(args[0]);
            if (name === 'getpos_getvalids_selection')
                args[0] = environment.selection(args[0]);
            if (name === 'gather_locs') {
                args[0] = environment.coordArrayPointer(args[0]);
                args[1] = environment.intPointer(args[1]);
            }
            if (name === 'truncate_to_map') {
                args[0] = environment.coordPointer(args[0]);
                args[1] = environment.coordPointer(args[1]);
            }
            const result = withCEnvironment(environment, getpos[name], ...args);
            return result?.address ?? result ?? 0;
        },
