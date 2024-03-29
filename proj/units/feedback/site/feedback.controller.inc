<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'feedback/site/feedback.actions.inc';
	require DIR_UNITS . 'feedback/site/feedback.model.inc';

	require DIR_UNITS . 'feedback/site/views/Form.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Instance;
	use Base\Helper\Response;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates\Feedback as TPL;
	use Closure;

	class Feedback extends Actions\Feedback {
		use Instance;

		private Model\Feedback $model;

		private function __construct() {
			parent::__construct(__FILE__);

			$this->model = Model\Feedback::instance();

			self::$view->Push([self::ENTRY_XHR], self::$feedback, Closure::fromCallable([$this, 'OnFeedback']));
			self::$view->Push([self::ENTRY_XHR], self::$do_feedback, Closure::fromCallable([$this, 'DoFeedback']));
		}

		#region XHR

		#[NoReturn] private function OnFeedback(): void {
			Response::PushData(['html' => TPL\Form::ToVar()]);
			Response::SendJSON();
		}

		#[NoReturn] private function DoFeedback(): void {
			$state = self::STATES['new'];
			$name = trim(GetParam('name', ''));
			$contacts = trim(GetParam('contacts', ''));
			$letter = trim(GetParam('letter', ''));
			$content = trim(GetParam('content', ''));

			if (($name === '') || ($content === '')) {
				Response::PushNoticeError('Поля <b>Имя</b> и <b>Содержание</b> обязательны для заполнения');
				Response::SendJSON();
			}

			$this->model->InsertFeedback($state, $name, $contacts, $letter, $content);

			Response::PushData([]);
			Response::SendJSON();
		}

		#endregion XHR

	}

	Feedback::init();