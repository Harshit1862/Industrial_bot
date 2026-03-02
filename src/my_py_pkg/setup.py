from setuptools import find_packages, setup

package_name = 'my_py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='harshit',
    maintainer_email='harshit20033@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
        'add_two_ints_client_no_oop = my_py_pkg.add_two_ints_client_no_oop:main',
        'add_two_ints_client = my_py_pkg.add_two_ints_client:main',
        'add_two_ints_server = my_py_pkg.add_two_ints_server:main',

        'battery_monitor = my_py_pkg.battery_monitor:main',
        'battery = my_py_pkg.battery:main',

        'cpu_monitor = my_py_pkg.cpu_monitor:main',
        'health_manager = my_py_pkg.health_manager:main',

        'led_panel = my_py_pkg.led_panel:main',

        'my_first_node = my_py_pkg.my_first_node:main',

        'publisher_member_function = my_py_pkg.publisher_member_function:main',
        'subscriber_member_function = my_py_pkg.subscriber_member_function:main',

        'robot_news_station = my_py_pkg.robot_news_station:main',
        'smartphone = my_py_pkg.smartphone:main',

        
        ],
    },
)
