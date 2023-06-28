<?php

	namespace Base\Editor\MySQLi\HTML;

	require DIR_BASE . 'editor/editor.html.inc';
	require DIR_BASE . 'editor/MySQLi/editor.model.inc';

	abstract class Editor extends \Base\Editor\HTML\Editor {

		public function __construct(string $name) {
			parent::__construct($name);
		}

	}