
NODE = node
VALGRIND = valgrind

test:
	@$(NODE) test/index.js

valgrind:
	@$(VALGRIND) --leak-check=yes node test/index.js

.PHONY: test valgrind

