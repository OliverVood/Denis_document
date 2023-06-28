<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.common.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\Editor\MySQLi\XHR\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Feedback extends Editor {
		use Common\feedback;

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->Init();

			$this->titleDoDelete = 'Запись удалена';

			$this->model = new Model\Feedback($table);
		}

	}