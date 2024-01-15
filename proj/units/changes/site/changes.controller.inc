<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'changes/site/changes.actions.inc';
	require DIR_UNITS . 'changes/site/changes.model.inc';

	require DIR_UNITS . 'changes/site/views/Last.tpl';
	require DIR_UNITS . 'changes/site/views/All.tpl';
	require DIR_UNITS . 'changes/site/views/Show.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates\Layout;
	use Proj\Site\Templates\Changes as TPL;
	use Redirect;

	class Changes extends Actions\Changes {
		use Instance;

		private Model\Changes $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Changes::instance();
		}

		#region HTML

		public function OnViewShow(): void {
			$id = GetInt('id');
			$changes = $this->model->GetChanges($id);

			if (!$changes) Redirect::Page404();

			Layout::instance()->main->Push(TPL\Show::ToVar($changes, $this->model->GetListChange($id)));
		}

		public function OnViewList(): void {
			Layout::instance()->main->Push(TPL\All::ToVar($this->model->GetLatestChanges(null), 'Все изменения'));
		}

		#endregion HTML

		public function GetViewLast(?int $count = null): string {
			return TPL\Last::ToVar($this->model->GetLatestChanges($count), 'Последние изменения на сайте');
		}

	}

	Changes::init();