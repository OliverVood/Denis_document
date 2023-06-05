<?php

	namespace Base\Editor\Skins;

	abstract class SkinBrowse extends Skin {

		public function __construct(string $title) {
			parent::__construct($title);
		}

	}

	require DIR_BASE . 'editor/skins/browse/elements/text.inc';
	require DIR_BASE . 'editor/skins/browse/elements/int2IP.inc';
	require DIR_BASE . 'editor/skins/browse/elements/valueFromArray.inc';
	require DIR_BASE . 'editor/skins/browse/elements/dateFormat.inc';
