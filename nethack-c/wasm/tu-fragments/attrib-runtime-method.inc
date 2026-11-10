        initializeAttrib(services) {
            let environment = attribEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createAttribEnvironment(services, layouts.attrib, attrib);
                attribEnvironments.set(services.moduleKey, environment);
            }
            return environment;
        },
        attrib(services, name, ...args) {
            let environment = attribEnvironments.get(services.moduleKey);
            if (!environment) {
                environment = createAttribEnvironment(services, layouts.attrib, attrib);
                attribEnvironments.set(services.moduleKey, environment);
            }
            if (name === 'gainstr') args[0] = environment.object(args[0]);
            if (['postadjabil', 'check_innate_abil', 'innately'].includes(name))
                args[0] = environment.longPointer(args[0]);
            const result = withCEnvironment(environment, attrib[name], ...args);
            return result?.address ?? result ?? 0;
        },
