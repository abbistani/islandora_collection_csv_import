# Islandora Collection CSV Import 

## Bug Warning

This module doens't add collection policies yet. If you use this, you won't be able to add to the collections using the GUI (though you can add to them programmatically) - May 20 2015

## Introduction

This module is for adding collection objects to Islandora using a .csv file. 

## Requirements

This module requires the following modules/libraries:
* [Islandora](https://github.com/islandora/islandora)
* [Islandora Basic Collection](https://github.com/Islandora/islandora_solution_pack_collection)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

CSV's must be properly prepared.  Any comma within a field (i.e. the LABEL field) must be replaced with
a double pipe ie - 'Nursing, Department of' must be replaced with
'Nursing|| Department of'

Do not use commas in the PID or PARENT fields.

If multiple arguments are supplied for the PARENT field, they must be
separated with a ~  ie islandora:root~islandora:basic_image_collection.

The CSV must contain the following columns:

* LABEL
* PID
* PARENT

Where LABEL is the label of the collection object to import, PID is a valid PID for this collection object (or a namespace,
in which case the PID will be assigned automatically), and PARENT is a list of pids (separated by ~) to which this collection
will have an isMemberOfCollection relationship.

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [Rosie Le Faive](https://github.com/rosiel)

## Development

If you would like to contribute to this module, please check out our helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the Islandora.ca site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
