        explode(services, name, ...args) {
            let environment = explodeEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createExplodeEnvironment(services, layouts.explode);
                explodeEnvironments.set(services.moduleKey, environment);
            }
            if (name === 'explosionmask') args[0] = environment.monster(args[0]);
            if (name === 'scatter') args[4] = environment.object(args[4]);
            if (name === 'explode_oil') args[0] = environment.object(args[0]);
            if (name === 'mon_explodes') {
                args[0] = environment.monster(args[0]); args[1] = environment.attack(args[1]);
            }
            const result = withCEnvironment(environment, explode[name], ...args);
            return result?.address ?? result ?? 0;
        },
