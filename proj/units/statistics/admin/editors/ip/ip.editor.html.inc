<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.common.inc';
	require DIR_UNITS . 'statistics/admin/editors/ip/ip.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Ip extends Editor {
		use Common\Ip;

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\Ip($table, $this->params);
		}

	}