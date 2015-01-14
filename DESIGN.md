# Design

moneyctl has two main parts: interface and core

## interface

interface is the part that user interact with either cli or ncurses or gtk
interface.

It should provide it main function and it will it seprate binaire.
It will initialize the core and execute its provided functions.

## core

Here are all interface independ functions. Main functions are defined on core.h
and other functions are defined on lib.h .

# Ascii representation

   +-------+      +-----------+

   | cli.c |      | ncurces.c |

   +---+---+      +-----+-----+

       |                |

       +------+ +-------+

	      | |

	  +---+-+---+

	  | core.c  |

	  +----+----+

	       |

 	   +---+---+

	   | lib.c |

	   +-------+
