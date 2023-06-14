<?php

	namespace Proj\Admin\Editor\Common;

	use Base\Controller;
	use Base\Editor\Skins\Browse;
	use Closure;

	trait Ip {

		private function Init(): void {
			$this->titleSelect = 'Статистика запросов к серверу';
		}

		protected function RegActions(): void {
			$this->RegActionSelect();
		}

		protected function SetHandlers(): void {
			Controller::$view->Push($this->select, Closure::fromCallable([$this, 'OnSelect']));
		}

		protected function ManageSelect(): array {
			return [];
		}

		protected function FieldsSelect(): array {
			return [
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'uid'		=> new Browse\Text('Пользователь'),
				'ip'		=> new Browse\Int2IP('IP адрес'),
				'path'		=> new Browse\Text('Путь'),
				'params'	=> new Browse\Text('Параметры')
			];
		}

	}