from setuptools import setup, find_packages

setup(
    name='lefdef',
    version='0.5.0',
    packages=find_packages(),
    package_data={
        'lefdef': ['lib/*.*'],
    },
    url='https://github.com/ruykaji/lefdef-python',
    license='MIT',
    author='ruykaji',
    description='A Python library for reading and writing LEF and DEF files.',
    install_requires=[
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
    ]
)