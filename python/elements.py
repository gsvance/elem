#!/usr/bin/env python

# Pretty simple script providing a useful reference to the periodic table of elements
# Give proton numbers, elemental symbols, or names of elements as arguments
# If an element matches the given argument, output that element's information

# Last edited 3/6/16 by Greg Vance

import sys

# Lookup table of elements' names and symbols organized by their proton number
elements = [	('n', 'Neutronium'),  # not quite legitimate...
		('H', 'Hydrogen'),
		('He', 'Helium'),
		('Li', 'Lithium'),
		('Be', 'Beryllium'),
		('B', 'Boron'),
		('C', 'Carbon'),
		('N', 'Nitrogen'),
		('O', 'Oxygen'),
		('F', 'Fluorine'),
		('Ne', 'Neon'),
		('Na', 'Sodium'),
		('Mg', 'Magnesium'),
		('Al', 'Aluminum'),
		('Si', 'Silicon'),
		('P', 'Phosphorus'),
		('S', 'Sulfur'),
		('Cl', 'Chlorine'),
		('Ar', 'Argon'),
		('K', 'Potassium'),
		('Ca', 'Calcium'),
		('Sc', 'Scandium'),
		('Ti', 'Titanium'),
		('V', 'Vanadium'),
		('Cr', 'Chromium'),
		('Mn', 'Manganese'),
		('Fe', 'Iron'),
		('Co', 'Cobalt'),
		('Ni', 'Nickel'),
		('Cu', 'Copper'),
		('Zn', 'Zinc'),
		('Ga', 'Gallium'),
		('Ge', 'Germanium'),
		('As', 'Arsenic'),
		('Se', 'Selenium'),
		('Br', 'Bromine'),
		('Kr', 'Krypton'),
		('Rb', 'Rubidium'),
		('Sr', 'Strontium'),
		('Y', 'Yttrium'),
		('Zr', 'Zirconium'),
		('Nb', 'Niobium'),
		('Mo', 'Molybdenum'),
		('Tc', 'Technetium'),
		('Ru', 'Ruthenium'),
		('Rh', 'Rhodium'),
		('Pd', 'Palladium'),
		('Ag', 'Silver'),
		('Cd', 'Cadmium'),
		('In', 'Indium'),
		('Sn', 'Tin'),
		('Sb', 'Antimony'),
		('Te', 'Tellurium'),
		('I', 'Iodine'),
		('Xe', 'Xenon'),
		('Cs', 'Caesium'),
		('Ba', 'Barium'),
		('La', 'Lanthanum'),
		('Ce', 'Cerium'),
		('Pr', 'Praseodymium'),
		('Nd', 'Neodymium'),
		('Pm', 'Promethium'),
		('Sm', 'Samarium'),
		('Eu', 'Europium'),
		('Gd', 'Gadolinium'),
		('Tb', 'Terbium'),
		('Dy', 'Dysprosium'),
		('Ho', 'Holmium'),
		('Er', 'Erbium'),
		('Tm', 'Thulium'),
		('Yb', 'Ytterbium'),
		('Lu', 'Lutetium'),
		('Hf', 'Hafnium'),
		('Ta', 'Tantalum'),
		('W', 'Tungsten'),
		('Re', 'Rhenium'),
		('Os', 'Osmium'),
		('Ir', 'Iridium'),
		('Pt', 'Platinum'),
		('Au', 'Gold'),
		('Hg', 'Mercury'),
		('Tl', 'Thallium'),
		('Pb', 'Lead'),
		('Bi', 'Bismuth'),
		('Po', 'Polonium'),
		('At', 'Astatine'),
		('Rn', 'Radon'),
		('Fr', 'Francium'),
		('Ra', 'Radium'),
		('Ac', 'Actinium'),
		('Th', 'Thorium'),
		('Pa', 'Protactinium'),
		('U', 'Uranium'),
		('Np', 'Neptunium'),
		('Pu', 'Plutonium'),
		('Am', 'Americium'),
		('Cm', 'Curium'),
		('Bk', 'Berkelium'),
		('Cf', 'Californium'),
		('Es', 'Einsteinium'),
		('Fm', 'Fermium'),
		('Md', 'Mendelevium'),
		('No', 'Nobelium'),
		('Lr', 'Lawrencium'),
		('Rf', 'Rutherfordium'),
		('Db', 'Dubnium'),
		('Sg', 'Seaborgium'),
		('Bh', 'Bohrium'),
		('Hs', 'Hassium'),
		('Mt', 'Meitnerium'),
		('Ds', 'Darmstadtium'),
		('Rg', 'Roentgenium'),
		('Cn', 'Copernicium'),
		('Uut', 'Ununtrium'),
		('Fl', 'Flerovium'),
		('Uup', 'Ununpentium'),
		('Lv', 'Livermorium'),
		('Uus', 'Ununseptium'),
		('Uuo', 'Ununoctium') ]

#  Complain if no args
if len(sys.argv) < 2:
	print 'elements: no args!'
	sys.exit(1)

# Print matching element for each arg, or a failure message
for arg in sys.argv[1:]:
	try:
		Z = int(arg) # try and see if we have a proton number
	except ValueError:
		string = arg.title() # Convert The Symbol Or Name To Title Case
		found = False
		for Z in xrange(len(elements)):
			if elements[Z][0] == string or elements[Z][1] == string: # check for match with name or symbol
				found = True
				break # Z is now set correctly, exit this search loop
		if not found: # we didn't find it
			print "No result for '%s'" % string
			continue
	if not 0 <= Z <= 118: # this isn't a usable proton number
		print "Z value '%s' not in range" % Z
		continue
	# Print the entry from the table if it was found
	print "%s\t%s\t%s" % (Z, elements[Z][0], elements[Z][1])

