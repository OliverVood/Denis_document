<?php

	namespace Base\Editor\Skins;

	abstract class SkinEditHTMLElement extends SkinEdit {
		protected string $name;

		public function __construct(string $title, string $name, string $default = '') {
			parent::__construct($title, $default);

			$this->name = $name;
		}

	}

	require DIR_BASE . 'editor/skins/edit/elements/input.inc';
	require DIR_BASE . 'editor/skins/edit/elements/text.inc';
	require DIR_BASE . 'editor/skins/edit/elements/datetime.inc';
	require DIR_BASE . 'editor/skins/edit/elements/hidden.inc';
	require DIR_BASE . 'editor/skins/edit/elements/file.inc';
	require DIR_BASE . 'editor/skins/edit/elements/textarea.inc';
	require DIR_BASE . 'editor/skins/edit/elements/select.inc';
//	require DIR_BASE . 'editor/skins/edit/elements/uploader.inc';