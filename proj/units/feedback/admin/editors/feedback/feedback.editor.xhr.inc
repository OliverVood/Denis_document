<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\Editor\XHR\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Feedback extends EditorMySQLi {
		use Model\feedback;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();

			$this->titleDoDelete = 'Запись удалена';
		}

	}