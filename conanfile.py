from conans import ConanFile, CMake


class RestServer(ConanFile):
    name = 'REST Server'
    version = '1.0.0'

    generators = [
        'cmake',
    ]

    options = {
        'shared': [True, False],
    }

    default_options = {
        'shared': True,
    }

    requires = [
        'poco/1.12.4',
        'soci/4.0.3',
        'nlohmann_json/3.11.2',
    ]

    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'

        cmake.configure()
        cmake.build()
