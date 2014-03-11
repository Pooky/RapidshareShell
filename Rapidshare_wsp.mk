.PHONY: clean All

All:
	@echo ----------Building project:[ Rapidshare - Debug ]----------
	@"$(MAKE)" -f "Rapidshare.mk"
clean:
	@echo ----------Cleaning project:[ Rapidshare - Debug ]----------
	@"$(MAKE)" -f "Rapidshare.mk" clean
