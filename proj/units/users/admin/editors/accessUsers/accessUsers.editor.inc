<?php

	namespace Proj\Admin\Editor;

	require DIR_UNITS . 'users/admin/editors/accessUsers/accessUsers.editor.model.inc';
	require DIR_UNITS . 'users/admin/editors/accessUsers/views/update.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Access;
	use Base\ActionRight;
	use Base\DB\MySQLi\Table;
	use Base\Editor\MySQLi\Editor;
	use Base\Helper\Response;
	use Proj\Templates\Editor\AccessUsers as TPL;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units;

	class AccessUsers extends Editor {

		public function __construct(int $id, string $name, Table $table, string $title = '') {
			parent::__construct($id, $name, $table, $title);

			$this->titleSelect = 'Список прав пользователя';
			$this->titleUpdate = 'Редактирование прав пользователя';
			$this->titleDoUpdate = 'Права пользователя установлены';

			$this->model = new Model\AccessUsers($table, $this->params);
		}

		protected function RegAccess() {
			$this->AddCollection();
			$this->AddRight(self::ACCESS_SETTING, 'setting', 'Назначение прав');
			$this->AddRight(self::ACCESS_UPDATE, 'update', 'Изменение');
		}

		protected function RegActionUpdate(): void { $this->update = new ActionRight($this->id, $this->name, 'update', "/{$this->name}/update?uid=%uid%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {uid: %uid%}); return false;"); }
		protected function RegActionDoUpdate(): void { $this->do_update = new ActionRight($this->id, $this->name, 'do_update', "/{$this->name}/do_update?uid=%uid%", /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this); return false;"); }

		protected function NavigateUpdate(): array { return [ function () { return Units\Users::instance()->editor_users->select->GetLinkHref('<< ' . Units\Users::instance()->editor_users->titleSelect, array_merge(['page' => 1], $this->params)); } ]; }

		#[NoReturn] protected function OnUpdate(): void {
			if (!Access::Allow(self::ACCESS_UPDATE, $this->id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$uid = GetInt('uid');

			$rights = Access::GetRights();
			$items = $this->model->GetAccessUser($uid);

			$navigate			= $this->NavigateUpdate();

			Response::PushHistory($this->update, array_merge(['uid' => $uid], $this->params));
			Response::PushSection('main', TPL\Update::ToVar($this, $uid, $rights, $items, "{$this->titleUpdate} #{$uid}", $navigate)/*, $this->params*/);
			Response::SendJSON();
		}

		#[NoReturn] protected function DoUpdate(): void {
			if (!Access::Allow(self::ACCESS_UPDATE, $this->id)) Response::SendNoticeError(self::TEXT_ERROR_ACCESS);

			$uid = GetInt('uid');
			$rights = GetParam('rights', []);

			$this->model->UpdateAccess($rights, $uid);

			Response::PushNoticeOk($this->titleDoUpdate);
			Response::SendJSON();
		}

	}