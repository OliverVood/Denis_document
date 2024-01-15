<?php

	namespace Base\Editor\MySQLi;

	require DIR_BASE . 'editor/editor.inc';
	require DIR_BASE . 'editor/MySQLi/editor.model.inc';

	use Base\DB\MySQLi\Table;

	abstract class Editor extends \Base\Editor\Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $title);
		}

	}