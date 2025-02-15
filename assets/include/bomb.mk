BOMB_DIR := assets/bomb

BOMB_PALETTE := $(BOMB_DIR)/gTLUTBomb.png

BOMB_FRAMES := \
$(BOMB_DIR)/gTextureBomb1.png \
$(BOMB_DIR)/gTextureBomb2.png \
$(BOMB_DIR)/gTextureBomb3.png \
$(BOMB_DIR)/gTextureBomb4.png

BOMB_EXPORT_SENTINEL := $(BOMB_DIR)/.export

$(BUILD_DIR)/src/common_textures.inc.o: $(BOMB_FRAMES:%.png=%.inc.c) $(BOMB_PALETTE:%.png=%.inc.c)

$(BOMB_FRAMES:%.png=%.inc.c): %.inc.c : %.png
	$(N64GRAPHICS) -Z $@ -g $< -s u8 -f ci8 -c rgba16 -p $(BOMB_PALETTE)

$(BOMB_PALETTE:%.png=%.inc.c): %.inc.c : %.png
	$(N64GRAPHICS) -i $@ -g $< -s u8 -f rgba16

$(BOMB_FRAMES) $(BOMB_PALETTE): $(BOMB_EXPORT_SENTINEL) ;

$(BOMB_EXPORT_SENTINEL): $(ASSET_DIR)/bomb.json
	$(ASSET_EXTRACT) $(BASEROM) $<
	touch $@

.PHONY: distclean_bomb
distclean_bomb:
	rm -rf $(BOMB_DIR)

distclean_assets: distclean_bomb
