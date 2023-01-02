from conans import ConanFile, CMake


class RestServer(ConanFile):
    name = 'REST Server'
    version = '1.0.0'

    generators = [
        'cmake',
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

    requires = [
        'poco/1.12.4',
        'soci/4.0.3',

        'libpq/14.5',
        'sqlite3/3.39.4',
        'libmysqlclient/8.0.30',

        'nlohmann_json/3.11.2',
    ]

    def configure(self):
        self.options['soci'].with_sqlite3 = self.options.with_sqlite3
        self.options['soci'].with_mysql = self.options.with_mysql
        self.options['soci'].with_postgresql = self.options.with_postgresql

    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = 'ON' if self.options.shared else 'OFF'

        cmake.configure()
        cmake.build()
