<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\EditorMySQLi\XHR\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;

	class Feedback extends Editor {
		use Model\feedback;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();

			$this->titleDoDelete = 'Запись удалена';
		}

	}