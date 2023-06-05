<?php

	namespace Base\Editor\Skins;

	abstract class SkinEdit extends Skin {
		protected ?string $default;

		public function __construct(string $title, string $default = '') {
			parent::__construct($title);

			$this->default = $default;
		}

	}

	require DIR_BASE . 'editor/skins/edit/skinEditHTMLElement.inc';