<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.common.inc';
	require DIR_UNITS . 'feedback/admin/editors/feedback/feedback.editor.model.inc';

	use Base\Editor\MySQLi\HTML\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;

	class Feedback extends Editor {
		use Common\Feedback;

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->Init();

			$this->model = new Model\Feedback($table);
		}

	}