<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'feedback/consts.inc';
	require DIR_UNITS . 'feedback/site/views/Form.inc';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Units;
	use Base\Instance;
	use Base\Action;
	use Proj\Units\Consts;
	use Proj\DBQuery;
	use Proj\Site\Templates\Feedback\Form;

	class Feedback extends Units implements Consts\Feedback {
		use Instance;

		private DBQuery $db;

		public Action $feedback;
		public Action $do_feedback;

		public function __construct() {
			parent::__construct(self::ID, self::NAME);
			$this->db = DBQuery::instance();

			$this->feedback = new Action(self::NAME, 'null', 'default', /* @lang JavaScript */ "Site.Feedback.On(); return false;");
			$this->do_feedback = new Action(self::NAME, 'do', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Site.Feedback.Do); return false;");

			Controller::instance()->view->Push($this->feedback, [$this, 'OnFeedback']);
			Controller::instance()->view->Push($this->do_feedback, [$this, 'DoFeedback']);
		}

		#[NoReturn] public function OnFeedback(): void {
			SendJSONSuccess(['html' => Form::object()->ToVar()]);
		}

		#[NoReturn] public function DoFeedback(): void {
			$state = self::STATES['new'];
			$name = trim(GetParam('name', ''));
			$contacts = trim(GetParam('contacts', ''));
			$letter = trim(GetParam('letter', ''));
			$content = trim(GetParam('content', ''));

			if (($name === '') || ($content === '')) SendNoticeError('Поля <b>Имя</b> и <b>Содержание</b> обязательны для заполнения');

			$this->db->Insert(self::TABLES['feedback'], [
				'state' => $state,
				'name' => $name,
				'contacts' => $contacts,
				'letter' => $letter,
				'content' => $content,
			]);

			SendJSONSuccess([]);
		}

	}

	Feedback::init();