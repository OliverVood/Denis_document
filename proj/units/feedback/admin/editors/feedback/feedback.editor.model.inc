<?php

	namespace Proj\Admin\Editor\Model;

	use Base\Editor\Skins\Browse;
	use Proj\Units\Consts;

	trait Feedback {

		private function Init(): void {
			$this->titleSelect = 'Список обратной связи';
			$this->titleBrowse = 'Обратная связь';
			$this->titleDelete = 'Удалить запись?';

			$this->querySelect->where('`state` != '. Consts\Feedback::STATES['delete'])->order('datecr', 'DESC')->order('id');

			$this->states = [
				Consts\Feedback::STATE_NEW => [
					Consts\Feedback::STATE_DONE
				]
			];
		}

		protected function FieldsSelect(): array {
			return [
				'id' 		=> new Browse\Text('#'),
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_VIEW),
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'name'		=> new Browse\Text('Имя'),
				'contacts'	=> new Browse\Text('Контакт'),
				'letter'	=> new Browse\Text('Тема сообщения')
			];
		}

		protected function FieldsBrowse(): array {
			return [
				'state' 	=> new Browse\ValueFromArray('Состояние', Consts\Feedback::STATES_VIEW),
				'datecr'	=> new Browse\DateFormat('Дата', 'd.m.Y H:i'),
				'name'		=> new Browse\Text('Имя'),
				'contacts'	=> new Browse\Text('Контакт'),
				'letter'	=> new Browse\Text('Тема сообщения'),
				'content'	=> new Browse\Text('Содержание')
			];
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->do_delete->GetLinkHref('Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLinkHref('Просмотреть', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return ($item['state'] == Consts\Feedback::STATE_NEW) ? $this->set_state->GetLinkHref('Проверена', array_merge(['id' => $item['id'], 'state' => Consts\Feedback::STATE_DONE], $this->params)) : ''; }
			];
		}

}