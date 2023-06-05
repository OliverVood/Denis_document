<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.model.inc';

	use Base\Editor\XHR\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Ip extends EditorMySQLi {
		use Model\Ip;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

	}