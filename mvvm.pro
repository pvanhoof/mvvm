TEMPLATE = subdirs

SUBDIRS = MVVM Examples

MVVM.file = "MVVM/MVVM.pro"
Examples.file = "Examples/Example.pro"

Examples.depends = MVVM
