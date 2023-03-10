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

        self.options['soci'].with_mysql = self.options.with_mysql
        self.options['soci'].with_sqlite3 = self.options.with_sqlite3
        self.options['soci'].with_postgresql = self.options.with_postgresql

    def requirements(self):
        self.requires('nlohmann_json/3.11.2')
        self.requires('poco/1.12.4')
        self.requires('soci/4.0.3')

        if self.options.with_sqlite3:
            self.requires('sqlite3/3.39.4')

        if self.options.with_mysql:
            self.requires('libpq/14.5')

        if self.options.with_postgresql:
            self.requires('libmysqlclient/8.0.30')

    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'

        cmake.configure()
        cmake.build()
