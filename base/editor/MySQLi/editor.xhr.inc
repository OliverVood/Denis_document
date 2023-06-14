<?php

	namespace Base\EditorMySQLi\XHR;

	require DIR_BASE . 'editor/editor.xhr.inc';
	require DIR_BASE . 'editor/MySQLi/editor.model.inc';

	abstract class Editor extends \Base\Editor\XHR\Editor {

		public function __construct(string $name) {
			parent::__construct($name);
		}

	}