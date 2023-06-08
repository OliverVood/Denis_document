<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;
	use Proj\Admin\Editor\Model;
	use Base\DB\TableMySQLi;

	class Ip extends Editor {
		use Model\Ip;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}