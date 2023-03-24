from conans import ConanFile, CMake


class RestServer(ConanFile):
    name = 'REST Server'
    version = '1.0.0'

    settings = [
        'os',
        'build_type',
        'arch',
    ]

    options = {
        'shared': [True, False],
        'with_sqlite3': [True, False],
        'with_mysql': [True, False],
        'with_postgresql': [True, False],
    }

    default_options = {
        'shared': True,
        'with_sqlite3': True,
        'with_mysql': True,
        'with_postgresql': True,
    }

    def configure(self):
        self.generators = [
            'cmake',
        ]

        self.options['poco'].enable_data_mysql = self.options.with_mysql
        self.options['poco'].enable_netssl = True
        self.options['poco'].enable_net = True

    def requirements(self):
        self.requires('nlohmann_json/3.11.2')
        self.requires('poco/1.12.4')

    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'

        cmake.configure()
        cmake.build()
