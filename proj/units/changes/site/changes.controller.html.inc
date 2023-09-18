<?php

	namespace Proj\Site\Units\HTML;

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
	use Closure;

	class Changes extends Actions\Changes {
		use Instance;

		private Model\Changes $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Changes::instance();

			self::$view->Push(self::$last, Closure::fromCallable([$this, 'OnViewLast']));
			self::$view->Push(self::$list, Closure::fromCallable([$this, 'OnViewList']));
			self::$view->Push(self::$show, Closure::fromCallable([$this, 'OnViewShow']));
		}

		private function OnViewShow(): void {
			$id = GetInt('id');
			$changes = $this->model->GetChanges($id);

			if (!$changes) Redirect::Page404();

			Layout::instance()->main->Push(TPL\Show::ToVar($changes, $this->model->GetListChange($id)));
		}

		private function OnViewLast(): void {
			Layout::instance()->main->Push(TPL\Last::ToVar($this->model->GetLatestChanges(4), 'Последние изменения на сайте'));
		}

		private function OnViewList(): void {
			Layout::instance()->main->Push(TPL\All::ToVar($this->model->GetLatestChanges(null), 'Все изменения'));
		}

	}

	Changes::init();