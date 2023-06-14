<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.common.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Feedback extends Editor {
		use Common\Feedback;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\Feedback($table);
		}

	}